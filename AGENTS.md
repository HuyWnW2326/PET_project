# PET Project - Agent Instructions

## Project

Target: STM32F103C8T6

Architecture: ARM Cortex-M3

Language: ISO C11

Toolchain: `arm-none-eabi-gcc`

Goal: Bare-metal firmware and a future MicroC/OS-II port.

## Authoritative conventions

Read and follow:

- `Docs/CODING_STANDARD.md` for project coding and organization rules.
- `.clang-format` for mechanically enforced layout.

Do not duplicate detailed style rules in this file. If these documents conflict, report and
reconcile the conflict before editing. Hardware specifications, the C language, the ABI, and
required linker, interrupt, startup, or RTOS interfaces take precedence over cosmetic rules.

## Architecture

- `App/`: application code.
- `Core/`: startup, vector table, RCC, clock configuration, and ARM Cortex-M3 infrastructure.
- `Drivers/`: reusable peripheral drivers.
- `OS/`: future MicroC/OS-II integration.

## Change workflow

1. Before broad refactoring, audit the affected files and read the applicable project conventions.
2. Inspect `git status` and the relevant diff before editing. Preserve unrelated and pre-existing
   changes in the worktree.
3. Keep each change within the requested scope. Do not refactor unrelated modules or introduce
   unnecessary abstractions.
4. Explain architectural changes and obtain approval before implementation.
5. Do not commit changes automatically.

## Modification constraints

- Preserve existing program behavior during style-only work.
- Do not modify register addresses, offsets, masks, bit values, or volatile semantics.
- Do not change hardware access ordering, startup behavior, vector-table contents or order, linker
  symbols, clock frequencies, public APIs, or interrupt-handler names without explicit approval.
- Do not modify the linker script without explicit approval.
- Do not introduce STM32 HAL, STM32 LL, or CMSIS peripheral-driver dependencies.
- Preserve ARM Cortex-M3 ABI requirements and required future MicroC/OS-II integration interfaces.
- Do not modify or restyle third-party MicroC/OS-II code during project refactoring.

## Verification

After editing project code:

1. Run clang-format on modified project-owned C and header files.
2. Run `make clean && make`.
3. Check compiler warnings.
4. Run `git diff --check` and review the complete diff.
5. Report every modified file and any verification that could not be performed.

For documentation-only or configuration-only work, run the checks relevant to those files and
validate any changed configuration with its intended tool version.

A successful build does not prove correct hardware behavior. Do not claim on-board verification
unless the firmware was flashed and tested on the target.
