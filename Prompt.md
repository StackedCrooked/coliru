# Prompt for continuing work (updated after cutover)

You are helping migrate the Coliru C++ runner site to Docker and to a new VPS. The repo is at `/home/francis/coliru`. The new VPS is **live** at `https://coliru.stacked-crooked.com`. The old VPS has been rsynced and is ready to be retired after final validation.

## Context summary

- The site is a Sinatra Ruby webserver that compiles/runs user C++ code.
- Runner is now a Docker container, launched by the webserver. Jobs are written to a shared Docker volume mounted at `/job`.
- `Web/build_and_run.sh` runs the runner container and passes limits.
- `CompileArchive` was renamed to `CompileCache` (config: `COLIRU_COMPILE_CACHE`).
- The webserver container runs as non-root `webserver` user.
- TLS/HTTPS was removed from the app code. TLS is handled by **Nginx on the host** (reverse proxy) with Let’s Encrypt.
- `SetupHost.sh` is an idempotent host setup script for Ubuntu 24.04:
  - Installs Docker, Nginx, certbot (for letsencrypt), sets up systemd service.
  - Supports `COLIRU_TLS_MODE` (`none`, `selfsigned`, `letsencrypt`), default `selfsigned`.
  - Defaults `COLIRU_DOMAIN=localhost` if not set.
  - If Ubuntu repo lacks `docker-compose-plugin`, it adds Docker’s official repo and installs it.
  - Creates archive dirs using `COLIRU_ARCHIVE_ROOT` (default `/`) and sets ownership (uid 2001, gid 2000).

## Recent changes

- Removed ACME challenge route from `Web/webserver-sinatra.rb`.
- Disabled default host blocking by setting `host_authorization` to allow `coliru.stacked-crooked.com`, `localhost`, `127.0.0.1`.
- Created docs: `LXD_TUTORIAL.md` and `ARCHITECTURE.md` (AI-generated notes included).
- LXD is used as a dev “host OS” for Nginx + Docker. Port 443 proxied from host to LXD.

## Archive migration status

Migration completed:
1) Branch `transition-archive3` created and deployed on old site.
2) New writes go to `Archive3`, reads search `Archive3 → Archive2 → Archive`.
3) `Archive` and `Archive2` rsynced to new VPS.
4) Final `Archive3` rsync done.
5) New VPS serving HTTPS with Let’s Encrypt.

## What to do next

- Post-cutover validation (compile/share, archive lookups).
- Confirm certbot renewal timer.
- Decommission old VPS after validation.

## Notes

- User prefers POSIX shell (no `BASH_SOURCE`).
- Keep webserver running as non-root inside container.
- The webserver shouldn’t handle TLS; Nginx should.
- Keep changes minimal on `master` to avoid disrupting the old site.
