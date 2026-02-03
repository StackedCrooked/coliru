# Todo (as of 2026-01-29)

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

## Known open items (from our todo list)

- Ensure **Let’s Encrypt renewal** (systemd timer via certbot) is wired into `SetupHost.sh` when `COLIRU_TLS_MODE=letsencrypt`.
- Startup script on reboot (fast start, cleanup old job artifacts) – deferred.
- Cleanup unused scripts / unused code – deferred.
- Archive migration plan and backup strategy (disk image vs file-level).
- Check if `restart.sh` is still needed; possibly remove.
- Confirm output length enforcement plan (currently shelved).

## Current problem / focus

**Archive migration** without downtime or missing files.
- Old site writes to `Archive` + `Archive2`.
- New VPS needs all archives, but old site still writes while you migrate.
- You do not want to rename `Archive2` because old links break.

### Proposed migration plan (Archive3 approach)

1) **Create a new git branch from `master`** to update the *old* site:
   - Suggested name: `transition-archive3`.
2) On that branch, make the **old site write new jobs to `Archive3`** instead of `Archive2`.
   - Keep reading from `Archive2` for existing links.
   - Optionally read `Archive3` too (if link routing depends on it).
3) Deploy that minimal change to the current server.
4) Start rsync of **Archive** and **Archive2** (large) to the new VPS. (done)
5) Final cutover: rsync **Archive3** (small) right before DNS switch.

## Suggested next steps (Monday)

1) **Branching for migration**
   - Create branch from `master`: `transition-archive3`.
   - Implement Archive3 write path + read path update.
   - Deploy to old server.

2) **Data transfer**
   - Archive/Archive2 rsync complete.
   - Just before cutover, rsync Archive3 for the delta.

3) **TLS on new VPS**
   - After DNS points to new VPS, run certbot once.
   - Ensure certbot timer is enabled for renewals.

4) **Return to Docker branch**
   - Continue Docker refactor + deployment on new VPS.

## Commands you’ll likely need

- Update old site with Archive3 change:
  - `git checkout master`
  - `git checkout -b transition-archive3`
  - edit code to write to Archive3
  - deploy on old server

- Rsync (examples):
  - `rsync -a --delete /path/to/Archive/ user@new:/path/Archive/`
  - `rsync -a --delete /path/to/Archive2/ user@new:/path/Archive2/`
  - `rsync -a --delete /path/to/Archive3/ user@new:/path/Archive3/`
