.PHONY: help setup build build-release build-lsp install-lsp dev-extension clean

# Default target - show help
help:
	@echo "PlainTasks Zed Extension - Build Commands"
	@echo ""
	@echo "Setup:"
	@echo "  make setup           - Install required Rust targets and build dependencies"
	@echo ""
	@echo "Development:"
	@echo "  make build           - Build extension (debug) and LSP server"
	@echo "  make build-release   - Build extension (release) and LSP server"
	@echo "  make dev-extension   - Build release and prepare for dev extension install"
	@echo ""
	@echo "LSP Server:"
	@echo "  make build-lsp       - Build LSP server (release)"
	@echo "  make install-lsp     - Build and install LSP server to ~/.cargo/bin/"
	@echo ""
	@echo "Cleanup:"
	@echo "  make clean           - Remove all build artifacts"
	@echo ""
	@echo "Quick Start for Dev Extension:"
	@echo "  1. make setup"
	@echo "  2. make install-lsp"
	@echo "  3. make dev-extension"
	@echo "  4. In Zed: Extensions → Install Dev Extension → Select this directory"

# Setup development environment
setup:
	@echo "Installing wasm32-wasip1 target..."
	rustup target add wasm32-wasip1
	@echo "Checking LSP dependencies..."
	cd lsp && cargo check
	@echo "✓ Setup complete"

# Build extension (debug)
build:
	@echo "Building extension (debug)..."
	cargo build --target wasm32-wasip1
	ln -sf target/wasm32-wasip1/debug/plaintasks.wasm extension.wasm
	@echo "✓ Extension built: extension.wasm -> target/wasm32-wasip1/debug/plaintasks.wasm"

# Build extension (release)
build-release:
	@echo "Building extension (release)..."
	cargo build --release --target wasm32-wasip1
	ln -sf target/wasm32-wasip1/release/plaintasks.wasm extension.wasm
	@echo "✓ Extension built: extension.wasm -> target/wasm32-wasip1/release/plaintasks.wasm"

# Build LSP server
build-lsp:
	@echo "Building LSP server (release)..."
	cd lsp && cargo build --release
	@echo "✓ LSP server built: lsp/target/release/plaintasks-lsp"

# Install LSP server to ~/.cargo/bin/
install-lsp: build-lsp
	@echo "Installing LSP server to ~/.cargo/bin/..."
	cp lsp/target/release/plaintasks-lsp ~/.cargo/bin/
	@echo "✓ LSP server installed: ~/.cargo/bin/plaintasks-lsp"

# Build everything for dev extension use
dev-extension: build-release install-lsp
	@echo ""
	@echo "✓ Build complete!"
	@echo ""
	@echo "Next steps:"
	@echo "  1. Open Zed"
	@echo "  2. Open Extensions panel (Cmd+Shift+X)"
	@echo "  3. Click 'Install Dev Extension'"
	@echo "  4. Select this directory: $(PWD)"
	@echo ""

# Clean all build artifacts
clean:
	@echo "Cleaning build artifacts..."
	cargo clean
	cd lsp && cargo clean
	rm -f extension.wasm
	@echo "✓ Clean complete"
