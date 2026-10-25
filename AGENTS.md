# PET Project - Agent Instructions

## Project

Target: STM32F103C8T6
Architecture: ARM Cortex-M3
Language: C11
Toolchain: arm-none-eabi-gcc
Goal: Bare-metal firmware and future MicroC/OS-II port.

## Coding Standard

Read and follow:

- Docs/CODING_STANDARD.md
- .clang-format

Docs/CODING_STANDARD.md is the authoritative coding
standard for project-owned source code.

.clang-format defines mechanical formatting rules.

If these files conflict, report the conflict before editing.

## Architecture

App/
- Application code.

Core/
- Startup, vector table, RCC, clock configuration,
  and ARM Cortex-M3 infrastructure.

Drivers/
- Reusable peripheral drivers.

OS/
- Future MicroC/OS-II integration.

## Modification Rules

1. Preserve existing program behavior.
2. Do not modify register addresses or bit definitions
   during style-only refactoring.
3. Do not modify startup or vector table logic without approval.
4. Do not modify the linker script without approval.
5. Do not modify clock frequencies without approval.
6. Do not rename public APIs without approval.
7. Preserve ABI-required interrupt handler names.
8. Do not introduce STM32 HAL or LL dependencies.
9. Do not refactor unrelated modules.
10. Do not create unnecessary abstractions.

## Code Style

- Use C11.
- Use 4 spaces for indentation.
- Use Allman braces.
- Follow the repository .clang-format file.
- Use project-specific include guards.
- Follow the naming rules in Docs/CODING_STANDARD.md.
- Write comments and API documentation in English.
- Use Doxygen comments for public APIs.
- Prefer explicit fixed-width integer types.

## Verification

After making changes:

1. Run clang-format on modified C/H files.
2. Run make clean && make.
3. Check compiler warnings.
4. Review git diff.
5. Report modified files.
6. Report any verification that could not be performed.

A successful build does not prove correct hardware behavior.

## Important

Do not modify third-party MicroC/OS-II source files
during project coding-style refactoring.

For architectural changes, explain the proposed changes
and wait for approval.
