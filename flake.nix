{
  description = "Display Manager on Linux VT";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs ,... }:
	let 
	system = "x86_64-linux";
	pkgs = nixpkgs.legacyPackages.${system};
	in
	{
		devShells.${system}.default = pkgs.mkShell {
			buildInputs = with pkgs; [
				clang-tools
				clang
				gnumake
			];

			shellHook = ''
			export SHELL=${pkgs.fish}/bin/fish
			exec $SHELL
			'';
		};
  };
}
