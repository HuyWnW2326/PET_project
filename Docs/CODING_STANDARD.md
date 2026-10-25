# PET Project Coding Standard

Status: Project convention

Target: STM32F103C8T6 (ARM Cortex-M3)

Language: ISO C11

Toolchain: `arm-none-eabi-gcc`, GNU Make, OpenOCD, and GDB

Goal: Maintainable bare-metal firmware prepared for a future MicroC/OS-II port.

## 1. Scope and precedence

This document is the source of truth for project-owned C code and its organization.
`.clang-format` defines mechanically enforceable layout. `AGENTS.md` defines the workflow for
making changes and refers to this document instead of duplicating detailed style rules.

If these documents conflict, report and reconcile the conflict before refactoring. Hardware
specifications, ISO C, the ARM Cortex-M3 ABI, and required linker, interrupt, startup, or RTOS
interfaces take precedence over cosmetic rules.

Do not restyle or otherwise modify third-party MicroC/OS-II code as part of project coding-style
work. Keep any separately approved upstream modifications isolated and documented.

## 2. Language and toolchain

- Use ISO C11 (`-std=c11`). Use GCC extensions only when hardware or toolchain integration
  requires them, such as startup attributes, interrupt aliases, or context-switch assembly.
- Keep `.clang-format` compatible with clang-format 14. `Language: Cpp` is retained only because
  clang-format uses its C/C++ parser for C source; it does not change the firmware language.
- Use fixed-width integer types for registers, protocol fields, and values whose width is part of
  their contract. Use ABI-required types where the interface requires them.
- Enable `-Wall -Wextra` and address warnings instead of suppressing them to make a build pass.
- Do not introduce STM32 HAL, STM32 LL, or CMSIS peripheral-driver dependencies. ARM core headers
  require an explicit project decision.
- Avoid heap allocation in low-level drivers unless explicitly approved.
- A successful build does not prove correct hardware behavior.

## 3. Naming

| Item | Convention | Example |
| --- | --- | --- |
| Source and header files | `snake_case` | `clock_config.c`, `rcc_regs.h` |
| Public function | `MODULE_Action()` | `RCC_EnableClock()` |
| Private function | `static MODULE_Action()` | `static RCC_IsValidPeripheral()` |
| Local variable or parameter | `snake_case` | `timeout_count`, `peripheral` |
| Private static file-scope variable | `snake_case` | `static uint32_t timeout_count;` |
| Exported global variable | `g_snake_case` | `g_system_ticks` |
| Macro or register bit mask | `UPPER_SNAKE_CASE` | `RCC_CR_PLLON` |
| Enum constant | `UPPER_SNAKE_CASE` | `RCC_ERROR_PLL` |
| Public type | `Module_Name_t` | `RCC_Status_t` |
| Register structure | `MODULE_TypeDef` | `RCC_TypeDef` |
| Register member | Reference-manual name | `CR`, `CFGR`, `APB2ENR` |

- Use descriptive names. Hardware abbreviations from the reference manual are acceptable.
- Exported globals must have documented ownership and synchronization. Keep them rare.
- `vector_table` is an approved exception to the exported-global prefix rule. Preserve its name.
- Preserve `main`, ABI-required exception and interrupt handlers, linker-defined symbols, startup
  entry points, and MicroC/OS-II integration names even when they do not match project naming.
- Avoid creating identifiers reserved by the C implementation. Leading-underscore linker symbols
  supplied by the linker script are required exceptions.
- Do not rename a public API solely for style. An approved naming migration must update its
  declarations, definitions, call sites, tests, and build references together.

## 4. Formatting

- Use 4 spaces for indentation and no tabs in C or header files.
- Use Allman braces for functions and control statements.
- Initializer braces may remain on the declaration line, for example
  `uint32_t values[] = {1U, 2U};`.
- Use a 100-character line-length target. Exceed it only when splitting an indivisible item would
  reduce clarity or alter required content.
- Align pointers with the variable or function name: `Type *pointer`.
- Declare one variable per statement.
- Use one blank line between top-level function definitions. Do not add blank lines between
  consecutive declarations unless they separate logical groups.
- Use spaces around binary operators and after commas.
- End every text file with one newline and remove trailing whitespace.
- Run clang-format only on project-owned C and header files. Do not format linker scripts,
  Makefiles, or third-party code with clang-format.

## 5. Variable declarations

- Prefer declarations near first use.
- Prefer initialization at declaration when an appropriate value is available.
- Do not add artificial initialization merely to initialize a variable. A variable assigned on all
  paths before use may remain uninitialized at declaration.
- Do not move a declaration or initializer when doing so changes execution order, volatile access
  timing, function-call side effects, or conditional execution.
- Preserve object lifetime and stack-use considerations when moving declarations into narrower
  scopes.

## 6. Source organization

Use the following order when the sections apply:

1. Includes.
2. Private macros and types.
3. File-scope variables.
4. Private helper functions.
5. Public function definitions.

Do not add empty section banners merely to represent an unused section. Keep related declarations
together, and use `static` for file-private functions and data.

## 7. Headers and dependencies

- Every header must use a unique guard derived from its complete project-relative path. Convert
  path separators and punctuation to underscores and uppercase the result, prefixed with `PET_`.
  For example, `Core/Inc/rcc.h` uses `PET_CORE_INC_RCC_H`.
- In a `.c` file with a matching module header, include that header first. Then include standard
  headers, followed by other project headers. Separate these groups with one blank line.
- A `.c` file without a matching header starts with the standard headers it uses, followed by
  project headers.
- Keep include ordering manual. `.clang-format` must retain `SortIncludes: Never`.
- Include every directly used declaration or type. Do not rely on transitive includes.
- Do not include `.c` files.
- Public headers contain public types, constants, and declarations. Keep implementation details in
  `.c` files or explicitly internal headers.
- Do not define externally linked variables in headers. Use `extern` declarations only when the
  interface requires them.
- Avoid circular dependencies.

## 8. Comments and documentation

- Write comments and API documentation in English.
- Put public API Doxygen documentation in the public header. Do not duplicate the complete API
  contract above its definition.
- Use Doxygen sections in this order when applicable: `@brief`, description, `@param`, `@return`,
  and `@note`.
- Use `@return` only for functions that return a value. State non-returning behavior in the
  description or an `@note`, not in `@return`.
- Document relevant side effects, clock prerequisites, blocking behavior, hardware state changes,
  and interrupt or task safety.
- Private helpers do not require Doxygen unless a documented contract adds useful information.
- Prefer comments that explain hardware rationale, timing, errata, reserved-bit handling, or
  ordering constraints. Avoid comments that merely repeat the statement below them.
- Keep comments synchronized with code. Remove stale or misleading comments.
- Preserve useful vector-table annotations that identify exception numbers, IRQ numbers, and
  reserved entries.

Example:

```c
/**
 * @brief Enable the clock for a supported peripheral.
 *
 * The enable-register write is read back before this function returns.
 *
 * @param peripheral Peripheral identifier.
 * @return RCC_OK on success; otherwise an RCC error code.
 * @note The caller must serialize concurrent RCC register updates.
 */
RCC_Status_t RCC_EnableClock(RCC_Peripheral_t peripheral);
```

## 9. Types, qualifiers, and shared state

- Preserve `volatile` semantics for memory-mapped registers and state shared with interrupts where
  appropriate. `volatile` does not provide atomicity or synchronization.
- Use `const` for read-only data and for pointers whose pointed-to data must not be modified, when
  doing so preserves the interface and behavior.
- Explicitly document ownership and synchronization of state shared by main code, interrupts, or
  future RTOS tasks.
- Do not rely on unspecified integer widths, signed overflow, or unaligned access.
- Check integer promotions, shifts, and masks. Prefer unsigned constants for register bit
  operations, for example `1UL << bit`.

## 10. Embedded and hardware safety

- Preserve register addresses, offsets, masks, bit values, reserved-bit handling, and register
  write semantics during style-only work.
- Preserve volatile access timing and hardware access ordering.
- Enable a peripheral clock before accessing its registers, following documented requirements.
- Use masked read-modify-write only where the register's semantics permit it. Do not use ordinary
  read-modify-write for write-one-to-clear, write-only, or other special-semantics registers.
- Prefer `GPIOx_BSRR` for GPIO set/reset operations where atomic pin updates matter.
- Use bounded readiness waits unless the approved startup design explicitly requires a safe halt.
  Document timeout units or state that a timeout is an iteration count.
- Treat interrupt and future task concurrency as design constraints. A read-modify-write sequence
  is not inherently thread-safe.
- Do not change startup flow, `.data` or `.bss` initialization, vector-table contents or order,
  linker symbols, clock configuration, public APIs, or interrupt-handler names during style work.
- Preserve HSE 8 MHz, PLL x9, SYSCLK/HCLK 72 MHz, APB1 36 MHz, APB2 72 MHz, and Flash wait states
  unless an approved functional change explicitly requires otherwise.

## 11. Architecture

```text
App/                 Application logic
Core/Inc, Core/Src/  Startup, vector table, clock setup, RCC, and core infrastructure
Drivers/Inc, Drivers/Src/
                     Reusable peripheral drivers
OS/                  Future MicroC/OS-II integration
Config/              Optional project/build configuration
Docs/                Project conventions and technical documentation
```

- Preserve `App/app.c` until a separately reviewed directory migration is approved.
- Keep RCC in `Core/` unless an architectural change is approved.
- Drivers may depend on Core services such as RCC. Core must not depend on application code or
  high-level drivers.
- Application code uses driver APIs rather than duplicating register-level implementation.
- Do not create speculative directories, modules, or abstractions.

## 12. ARM Cortex-M3 and MicroC/OS-II exceptions

- Preserve ARM Cortex-M3 calling conventions, exception entry requirements, stack alignment,
  interrupt priorities, and vector-table layout.
- Startup code, exception handlers, interrupt handlers, weak aliases, section attributes, inline
  assembly, and linker symbols may require exact names or compiler-specific syntax.
- Preserve future MicroC/OS-II port interfaces, calling conventions, stack-frame layout,
  critical-section semantics, context-switch handlers, hooks, and configuration names.
- Do not apply project naming or formatting rules to third-party MicroC/OS-II kernel internals.
  Project-owned adaptation layers follow this standard unless an external interface requires an
  exception.
- Keep every exception narrow, explicit, and documented near the affected interface when useful.

## 13. Verification

Before broad refactoring, audit the affected files and inspect existing Git modifications. Preserve
unrelated user changes.

After editing project code:

1. Run clang-format on modified project-owned C and header files.
2. Run `make clean && make`.
3. Inspect compiler warnings.
4. Run `git diff --check` and review the complete diff.
5. Report modified files and any verification that could not be performed.

Do not claim on-board verification unless the firmware was flashed and tested on hardware. Do not
commit changes automatically.
