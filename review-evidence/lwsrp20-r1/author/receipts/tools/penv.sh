# The parent's tool environment (the qualification lane's: pinned RV32 SDK read only, pinned Verilator, offline netlist).
S=<scratch>; SDK=<rv32-sdk>
V=<tools>/pinned-verilator-5.050
export HOME=$S/home TMPDIR=$S/tmpdir VERILATOR=$V/verilator PYTHONHASHSEED=0
export COURSIER_MODE=offline SBT_OPTS=-Dsbt.offline=true LITEX_ENV_CC_TRIPLE=riscv32-linux
export PATH=<litex-tree>/venv/bin:$V:<tools>/sv2v-v0.0.12:$VALIDATION_STORAGE/scratch/a662/make43/bin:/usr/local/bin:/usr/bin:/bin:$SDK/host/bin
export TSN_GEN_ROOT=<management>/tools/tsn-gen-deca300c GIT_ALLOW_PROTOCOL=file:https
