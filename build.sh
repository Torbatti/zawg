mkdir -p build
mkdir -p local

# zig cc ./app-zawg/src/zawg.c -o build/zawg -g3 -ldl -lX11 -Ivendor/
gcc ./app-zawg/src/zawg.c -o build/zawg -g3 -ldl -lX11 -Ivendor/ -fsanitize=address
