# Coliru Architecture

_Last updated: 2026-01-29_
_Note: This document is AI-generated and should be reviewed for accuracy._

This document describes the current Coliru architecture, its major components, runtime flow, and operational assumptions. It should be updated as the system evolves.

---

## 1) High-Level Overview

Coliru is a web service that accepts C++ (and shell) jobs and runs them in a sandboxed environment. The current architecture uses two primary containers:

- **Webserver container**: handles HTTP requests, parses input, and orchestrates job execution.
- **Runner container**: performs compile/run in a constrained environment.

A **reverse proxy** (planned on the host OS) will terminate TLS and forward HTTP traffic to the webserver container.

---

## 2) Components

### 2.1 Webserver
- **Location**: `Web/`
- **Entry**: `Web/webserver-sinatra.rb`
- **Purpose**: Serves UI and API endpoints (`/compile`, `/sh`, `/share`, etc.)
- **Runtime user**: `webserver` (non-root inside container)

Key endpoints:
- `/compile`: JSON input (`cmd`, `src`) → compile/run → return output
- `/sh`: execute arbitrary shell command
- `/share`: write job files to archive

### 2.2 Runner
- **Location**: `Docker/runner/`
- **Purpose**: Run jobs with limits (CPU, memory, ulimits, no network)
- **Invocation**: via `Web/build_and_run.sh` using `docker run`

### 2.3 Shared Job Volume
- A named Docker volume (currently `coliru_jobs`) shared between webserver and runner.
- Job dirs are created under `COLIRU_JOB_ROOT` (default `/job`).

### 2.4 Archives
- `Archive` and `Archive2` hold user-submitted program files and outputs.
- These are mounted into the webserver container for viewing/sharing.
- **Compile cache** is stored under `COLIRU_COMPILE_CACHE` (default `/tmp/CompileCache`).

---

## 3) Runtime Flow (Compile)

1. **Request received** at `/compile` in `webserver-sinatra.rb`.
2. Webserver writes `cmd.sh` and `main.cpp` into a job dir: `${COLIRU_JOB_ROOT}/<id>`.
3. Webserver calls `sandbox.sh`.
4. `sandbox.sh` checks compile cache; if miss, it calls `build_and_run.sh`.
5. `build_and_run.sh` launches the runner container with:
   - no network
   - resource limits
   - mounted job dir
6. Runner executes `cmd.sh` and returns output to webserver.
7. Webserver returns output to caller.

---

## 4) Limits & Sandbox

Current enforcement is done in the runner container:
- **No network** (`--network=none`)
- **Read-only filesystem** with tmpfs `/tmp`
- **CPU/memory limits** via Docker
- **Ulimits** for process count and file size
- **Wall-clock timeout** enforced in runner entrypoint

Webserver also enforces:
- Output read limit (defensive)
- Request timeout (outer safety net)

---

## 5) Reverse Proxy (Host)

Planned approach:
- **Nginx** on host OS terminates TLS
- Proxies traffic to `http://127.0.0.1:8080` (webserver container)

This removes TLS handling from `webserver-sinatra.rb` and `_restart_https.sh`.

---

## 6) Deployment & Host Setup

- `SetupHost.sh` performs host provisioning:
  - installs Docker + Nginx
  - configures Nginx reverse proxy
  - installs systemd unit (`coliru.service`)
  - starts the stack via `docker compose up -d`

---

## 7) Persistence & Data

- **Archive / Archive2**: persistent, migrated between VPSs
- **Compile cache**: local, disposable, not part of share links
- **Job dirs**: ephemeral, should be cleaned (cleanup strategy deferred)

---

## 8) Known Deferred Items

- Host startup cleanup for job dirs
- Output truncation behavior finalized (truncate vs kill)
- Backup and migration strategy for Archive/Archive2
- Remove legacy scripts and unused code

---

## 9) Conventions

- Runtime configs are controlled by environment variables, typically from `docker-compose.yml`.
- Non-root user inside webserver container is preferred.

---

_End of document_
