PET Project Coding Standard
Status: Project convention
Target: STM32F103C8T6 (ARM Cortex-M3)
Language: ISO C11 (GNU extensions only where hardware/toolchain integration requires them)
Toolchain: arm-none-eabi-gcc, GNU Make, OpenOCD, GDB
Goal: Maintainable bare-metal firmware, prepared for a future µC/OS-II port.
1. Scope and precedence
This document is the single source of truth for project-owned C code and its organization. .clang-format is authoritative for mechanically enforceable whitespace and layout. AGENTS.md and .github/copilot-instructions.md reference this document rather than redefining it.
When rules conflict, report the conflict and reconcile the documents before refactoring. Do not silently reinterpret the rules. Hardware specifications, the C language, the ABI, and required linker/interrupt symbol names override cosmetic naming rules.
Do not restyle third-party µC/OS-II sources unless explicitly requested; keep upstream modifications isolated and documented.
2. Language and build
- Use C11 (-std=c11), with narrowly justified GCC attributes or assembly for startup, interrupts, and context switching.
- Use fixed-width integer types (uint8_t, uint16_t, uint32_t, etc.) for register and protocol data.
- Enable -Wall -Wextra and address warnings; do not suppress warnings merely to make a build pass.
- Avoid heap allocation in low-level drivers unless explicitly approved.
- Do not use STM32 HAL, STM32 LL, or CMSIS peripheral drivers. ARM core headers may be considered only by explicit project decision.
- Do not assume a successful build proves correct hardware operation.
3. Names
Item	Convention	Example
Source/header files	snake_case	clock_config.c, rcc_regs.h
Public API	MODULE_Action()	RCC_EnableClock(), CLOCK_ConfigSystem()
Private function	MODULE_Action() with static	RCC_IsValidPeripheral()
Local variable/parameter	snake_case	timeout_count, peripheral
File-scope variable	snake_case, static when private	static uint32_t timeout_count;
Exported global (rare)	g_ prefix, documented ownership	g_system_ticks
Macros/register bit masks	UPPER_SNAKE_CASE	RCC_CR_PLLON
Enum constants	UPPER_SNAKE_CASE	RCC_ERROR_PLL
Public types	Module_Name_t	RCC_Status_t
Register structures	MODULE_TypeDef	RCC_TypeDef
Register members	Reference manual names	CR, CFGR, APB2ENR


- Use descriptive names; avoid unexplained abbreviations.
- Do not rename ABI-required symbols: Reset_Handler, SysTick_Handler, PendSV_Handler, SVC_Handler, other vector handlers, linker-defined symbols, or µC/OS-II port interfaces.
- Avoid creating identifiers reserved by the C implementation (notably leading underscores at file scope). Existing linker/toolchain-required names are documented exceptions.
- A deliberate naming migration must update declarations, definitions, call sites, tests, and build references together.
4. Formatting
- Follow the repository .clang-format file.
- Use 4 spaces for indentation, never tabs in C/H files.
- Use Allman braces ({ on a separate line).
- Limit lines to approximately 100 characters.
- Use one blank line between top-level function definitions; no extra blank lines between consecutive prototypes unless separating logical groups.
- Use spaces around binary operators and after commas.
- End every text file with one newline; avoid trailing whitespace.
- Format only project-owned C/H files; do not format linker scripts or Makefiles using clang-format.
5. Headers and dependencies
- Every header uses a unique include guard based on its project-relative path, e.g. PET_CORE_RCC_H or PET_DRIVERS_GPIO_H.
- Include the matching module header first in each .c file, then standard headers, then other project headers; separate groups with a blank line when useful.
- Include what the file uses directly; do not rely on accidental transitive includes.
- Do not #include .c files.
- Public headers contain public types, constants, and declarations; internal implementation details stay in .c files or explicitly internal headers.
- Do not define externally linked global variables in headers; use extern declarations only when justified.
- Avoid circular dependencies. Use static for file-private functions and data.
- Existing guards may be migrated when touching a header, provided all builds continue to work.
6. Comments and documentation
- Write comments and API documentation in English.
- Document public functions with Doxygen @brief, @param, and @return where applicable. Explain side effects, clock prerequisites, blocking behavior, and interrupt safety when relevant.
- Comment why a hardware sequence is required (timing, errata, reserved bits, ordering), not merely what a statement does.
- Keep comments synchronized with code; remove stale or misleading comments.
- Keep private helpers self-explanatory; add comments only when their intent is non-obvious.
Example:
/**
 * @brief Enable the clock for a supported peripheral.
 *
 * @param peripheral Peripheral identifier.
 * @return RCC_OK on success; otherwise an RCC error code.
 */
RCC_Status_t RCC_EnableClock(RCC_Peripheral_t peripheral);
7. Types, qualifiers, and shared state
- Use volatile for memory-mapped register accesses and state shared with interrupts when appropriate. volatile does not make accesses atomic or provide synchronization.
- Use const for read-only data and pointers where the pointed-to data must not be modified.
- Use static for internal linkage; do not use a global variable where a local variable is sufficient.
- Explicitly document ownership and synchronization of ISR/main or RTOS-shared state.
- Do not rely on unspecified integer widths, signed overflow, or unaligned access.
- Check integer promotions, shifts, and masks; prefer unsigned constants for register bit operations (e.g. 1UL << bit).
8. Bare-metal register access
- Define register layouts with correct widths, offsets, and volatile members. Verify addresses and bit definitions against STM32F103 documentation (RM0008 and device datasheet).
- Enable the relevant peripheral clock before accessing its registers, following documented hardware requirements.
- Preserve reserved bits on writes unless the reference manual explicitly requires a different value.
- Use masked read-modify-write only for registers whose write semantics permit it.
- Never use ordinary read-modify-write for write-one-to-clear, write-only, or other special-semantics registers without checking the reference manual.
- Prefer GPIOx_BSRR for GPIO set/reset operations where atomic pin updates matter.
- Use bounded timeouts for hardware readiness waits; return or report failures rather than hanging silently unless startup design explicitly requires a safe halt.
- Document ordering requirements and readbacks where necessary.
- Avoid magic register values when a named mask or field definition makes intent clearer.
- Treat concurrency, interrupts, and future RTOS tasks as design constraints; read-modify-write sequences are not inherently thread-safe.
9. Modules and directories
App/                 Application logic
Core/Inc, Core/Src/  Startup, vector table, clock setup, RCC, core infrastructure
Drivers/Inc, Drivers/Src/
                     Reusable peripheral drivers (GPIO, UART, SPI, I2C, timers)
OS/                  Future µC/OS-II integration (create when needed)
Config/              Optional project/build configuration (create when needed)
Docs/                Project conventions and technical documentation
- Preserve the current App/app.c location until a separate, reviewed directory migration is requested.
- Keep RCC in Core/ for this project unless an explicit architecture change is approved.
- Drivers may depend on Core services such as RCC; Core must not depend on application code or high-level drivers.
- Application code calls driver APIs instead of duplicating register-level implementation.
- Do not create speculative folders, modules, or abstractions merely to match a proposed tree.
10. Error handling and testing
- Use explicit status/error types for operations that can fail.
- Validate public API arguments where practical; avoid undefined shifts or invalid peripheral pointers.
- Keep timeout behavior deterministic and document units.
- After edits, run make clean && make, inspect warnings, and review git diff.
- For a style-only refactor, preserve startup flow, .data/.bss initialization, vector order, linker symbols, RCC behavior, HSE 8 MHz, PLL x9, SYSCLK/HCLK 72 MHz, APB1 36 MHz, APB2 72 MHz, and Flash wait states.
- Do not claim on-board verification unless the firmware was actually flashed and tested.
11. Exceptions and future RTOS port
- Startup, exception handlers, assembly context switching, linker-defined symbols, and vendor/µC/OS-II integration points may require exact external names and compiler-specific constructs.
- Keep these exceptions explicit and documented; do not rename them solely to satisfy style conventions.
- For future µC/OS-II integration, preserve calling conventions, stack alignment, interrupt priorities, critical-section semantics, and required hook names.
- Do not modify third-party kernel internals during a coding-style refactor.
