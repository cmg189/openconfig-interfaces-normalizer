# openconfig-interfaces-normalizer

This project is a C program that reads an `openconfig-interfaces`
json file and normalizes the configuration into a data structure representing a device's interface configuration.

One area that this project is useful for is taking a vendor's rendering of a standard YANG model,
resolving the vendor-specific encodings and augments,
and producing a representation that external applications can process without knowing which
NOS it came from.

## The problem

[OpenConfig](https://openconfig.net/) defines a vendor-neutral model, but the json that comes from a real device is
messier than the model suggests:

- **Identityrefs carry module prefixes.** `port-speed` arrives as
  `"openconfig-if-ethernet:SPEED_25GB"` on some platforms and `"SPEED_25GB"` on others.
  [RFC 7951](https://www.rfc-editor.org/rfc/rfc7951) makes the prefix optional when the
  leaf and its parent share a module, so both are valid and both must be handled.
- **Vendor augments use their own conventions.** `openconfig-if-ethernet-ext2:advertised-speed`
  is a numeric string in Mbit/s (`"25000"`), not an identityref — a different encoding for
  the same physical property the standard `port-speed` leaf describes.
- **Absent is not false.** OpenConfig gives `enabled` a default of `true`. A device that
  omits the leaf is reporting an enabled interface, not a disabled one. Collapsing the two
  is the kind of bug that surfaces as a mystery outages, so unset fields are
  tracked distinctly from set-to-false ones.

Normalizing configuration helps resolve these problems.

## What this project does

Traverses `openconfig-interfaces:interfaces/interface[name]` and builds a sorted linked list of
interface configurations, populating:

| Field | Source leaf |
|---|---|
| `if_name` | `name` |
| `type` | `config/type` |
| `description` | `config/description` |
| `enabled` | `config/enabled` |
| `mtu` | `config/mtu` |
| `speed` | `openconfig-if-ethernet:ethernet/config/port-speed` |
| `advertised_speed` | `openconfig-if-ethernet:ethernet/config/openconfig-if-ethernet-ext2:advertised-speed` |
| `auto_negotiate` | `openconfig-if-ethernet:ethernet/config/auto-negotiate` |

## Layout

```
switch.c            entry point: generate json from file, start initalization and output of data structure, memory cleanup
switch.h            shared types, status enum, logging macros
switch_generate.c   openconfig-interfaces traversal and data extraction
switch_utils.c      data structure: initalize, output, and memory allocation
```

The split is deliberate: `switch_generate` knows the openconfig-interfaces schema and nothing about
storage. `switch_utils` knows the data structure and nothing about json. This organizes the knowledge among various modules.

## Build

Requires a C11 compiler and [json-c](https://github.com/json-c/json-c).

```sh
# Debian/Ubuntu
sudo apt install libjson-c-dev

make            # build ./switch
make run        # build and run against the bundled sample
make check      # run under AddressSanitizer + UBSan with leak detection
make strict     # build with -Werror
make clean
```

## Usage

```sh
./switch [path/to/interfaces.json]
```

Defaults to `openconfig-interfaces-data.json` if no path is given. Exits non-zero on a
missing or malformed file. Diagnostics go to stderr, the port listing to stdout.

## Sample output

```
Eth1/1
    type: ethernetCsmacd
    description: N/A
    enabled: 1
    speed: 25GB
    advertised_speed: 25000 Mbps
    mtu: 9100
    auto_negotiate: 1
```

## Design notes

**Tri-state fields.** Numeric fields initialize to `-1` and string fields to `"UNKNOWN"`,
so "the device did not report this" is distinguishable from a real value. A parser that
zero-fills cannot tell you whether an MTU of 0 means unset or misconfigured.

**Single cleanup path.** `main` uses `goto cleanup` so every resource is released in
exactly one place regardless of where a failure occurs. Duplicated teardown blocks are
where leaks accumulate.

**Status enum over bare ints.** Callers can distinguish "port not found" from "null
argument" from "already present", which makes the log output diagnostic rather than
just alarming.

**Sanitizers in the build.** `make check` runs the full parse under ASan and UBSan with
leak detection enabled, so memory errors fail the build rather than waiting for a crash
in the field.
