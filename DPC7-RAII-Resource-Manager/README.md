# DPC7 RAII Resource Manager

Focus:

- RAII wrappers
- `pImpl`
- scoped cleanup

Students wrap fake engine resources in move-only handles and hide subsystem
details behind a `pImpl` boundary instead of scattering manual cleanup logic.
