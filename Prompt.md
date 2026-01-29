# Prompt for continuing work

You are helping migrate the Coliru C++ runner site to Docker and to a new VPS. The repo is at `/home/francis/coliru`. We are currently working on branch **`docker`** for the containerized refactor; the old site still runs from **`master`**.

## Context summary

- The site is a Sinatra Ruby webserver that compiles/runs user C++ code.
- Runner is now a Docker container, launched by the webserver. Jobs are written to a shared Docker volume mounted at `/job`.
- `Web/build_and_run.sh` runs the runner container and passes limits.
- `CompileArchive` was renamed to `CompileCache` (config: `COLIRU_COMPILE_CACHE`).
- The webserver container runs as non-root `webserver` user.
- TLS/HTTPS was removed from the app code. TLS is handled by **Nginx on the host** (reverse proxy).
- `SetupHost.sh` is an idempotent host setup script for Ubuntu 24.04:
  - Installs Docker, Nginx, certbot (for letsencrypt), sets up systemd service.
  - Supports `COLIRU_TLS_MODE` (`none`, `selfsigned`, `letsencrypt`), default `selfsigned`.
  - Defaults `COLIRU_DOMAIN=localhost` if not set.

## Recent changes

- Removed ACME challenge route from `Web/webserver-sinatra.rb`.
- Created docs: `LXD_TUTORIAL.md` and `ARCHITECTURE.md` (AI-generated notes included).
- LXD is used as a dev “host OS” for Nginx + Docker. Port 443 proxied from host to LXD.

## Main open issue: archive migration

Old site writes to `Archive` and `Archive2` (hundreds of thousands of files). You need to move data to a new VPS without missing files. Renaming `Archive2` breaks old links, so you need an **Archive3** strategy.

Proposed plan:
1) Create branch from `master` named `transition-archive3`.
2) On this branch, modify **old site** to write new jobs to `Archive3` (keep reads from `Archive2`).
3) Deploy that minimal change to the old server.
4) Start rsync of `Archive` + `Archive2` to the new VPS (large, long).
5) Just before cutover, rsync `Archive3` (small, final delta).

## What to do next

- Help identify where in the old code to change write path from `Archive2` → `Archive3` and update reads if needed.
- Provide exact edits and deploy steps.
- Later: add certbot auto-renewal to `SetupHost.sh` (enable `certbot.timer` when `COLIRU_TLS_MODE=letsencrypt`).

## Notes

- User prefers POSIX shell (no `BASH_SOURCE`).
- Keep webserver running as non-root inside container.
- The webserver shouldn’t handle TLS; Nginx should.
- Keep changes minimal on `master` to avoid disrupting the old site.
