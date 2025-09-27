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
		devShells.${system}.default = pkgs.mkShellNoCC {
			buildInputs = with pkgs; [
			  bear
				pkg-config
				clang-tools
				clang
				gnumake
				pam
				systemdLibs
			];

			shellHook = ''
			export SHELL=${pkgs.fish}/bin/fish
			make setup
			bear -- make
			exec $SHELL
			'';
		};
  };
}
