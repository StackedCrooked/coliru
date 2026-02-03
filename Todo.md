# Todo (as of 2026-02-03)

> Note: AI-generated summary based on our recent work.

## What’s already done

- **Docker refactor** on the `docker` branch:
  - Webserver runs in Docker (Ubuntu 24.04, system Ruby).
  - Runner runs in Docker with resource limits; jobs use a shared Docker volume mounted at `/job`.
  - Compile cache directory renamed from `CompileArchive` to `CompileCache` and used by the webserver.
  - Webserver now runs as non-root **webserver** user inside the container.
  - Host reverse proxy approach chosen (Nginx on host). TLS handled at host, not in app.

- **HTTPS removed from app code**:
  - Removed TLS handling from `Web/webserver-sinatra.rb`.
  - `_restart_https.sh` removed earlier; `Web/restart.sh` no longer does HTTPS.
  - ACME challenge route removed from `Web/webserver-sinatra.rb`.

- **SetupHost.sh** created/updated:
  - Idempotent host setup for Nginx + Docker + systemd unit.
  - Supports TLS modes via `COLIRU_TLS_MODE`: `none`, `selfsigned` (default), `letsencrypt`.
  - Defaults: `COLIRU_DOMAIN=localhost`, `COLIRU_PORT=8080`.
  - Builds runner image as part of setup so the webserver can spawn jobs.

- **Docs added/updated**:
  - `LXD_TUTORIAL.md` (includes LXD setup steps and TLS modes).
  - `ARCHITECTURE.md` (architecture overview). Both include AI-generated note.

- **LXD dev environment**:
  - LXD container used as “host OS” for Nginx + Docker.
  - LXD proxy ports for 80/443 (443 works with self-signed cert in dev).
- **Archive migration in progress**:
  - Old site writes to `Archive3`.
  - `Archive` and `Archive2` have been rsynced to the new VPS.
  - Final `Archive3` rsync done; new site is live.

## Known open items (from our todo list)

- Ensure **Let’s Encrypt renewal** (systemd timer via certbot) is wired into `SetupHost.sh` when `COLIRU_TLS_MODE=letsencrypt`.
- Startup script on reboot (fast start, cleanup old job artifacts) – deferred.
- Cleanup unused scripts / unused code – deferred.
- Archive migration plan and backup strategy (disk image vs file-level).
- Check if `restart.sh` is still needed; possibly remove.
- Confirm output length enforcement plan (currently shelved).

## Current problem / focus

**Post-cutover validation and cleanup.**
- Confirm archive lookups, compile/share, and HTTPS.
- Final shutdown of old VPS after validation.

### Migration status (Archive3 approach)

- Branch `transition-archive3` created and deployed to old site.
- New writes go to `Archive3`; reads search Archive3 → Archive2 → Archive.
- `Archive` and `Archive2` rsynced to new VPS.
- Final `Archive3` rsync completed.
- New VPS serving HTTPS.

## Next steps

1) **Validation**
   - Test `/compile`, `/share`, and `/a/<id>/main.cpp` publicly.
   - Spot-check old archive IDs.

2) **Old VPS shutdown**
   - Confirm no remaining dependencies on the old host.
   - Cancel Rackspace VPS.

3) **TLS renewal**
   - Confirm certbot timer is active.

4) **Cleanup**
   - Remove/flag deprecated scripts.
   - Revisit output truncation + job cleanup plan.

## Commands you’ll likely need

- Validate:
  - `curl -I https://coliru.stacked-crooked.com`
  - `curl -H 'Content-Type: application/json' -d '{"cmd":"g++ main.cpp && ./a.out","src":"#include <iostream>\nint main(){ std::cout << \"Hello World!\" << std::endl; }"}' https://coliru.stacked-crooked.com/compile`
