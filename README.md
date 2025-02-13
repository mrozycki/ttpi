Erika Typewriter Hacking Playground
=====

Local development setup
---

### Using nix
#### Setup

1. Install nix by following instructions at https://nixos.org/download
2. Add the following line to /etc/nix/nix.conf:

    experimental-features = nix-command flakes

3. (optional) Install direnv and direnv VSCode extension.

#### Workflow

Use `nix develop` to enter development shell. From there you'll have access to any tools and dependencies needed for development.