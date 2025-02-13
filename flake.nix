{
  description = "Flake utils demo";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixpkgs-24.11-darwin";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system: 
      let 
        pkgs = nixpkgs.legacyPackages.${system}; 
        pico-sdk-with-sm = (pkgs.pico-sdk.override { withSubmodules = true; });
      in {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc-arm-embedded
            cmake
            gnumake
            git
            openocd
            pico-sdk-with-sm
            picotool
          ];
          
          shellHook = ''
            # ...
            export PICO_SDK_PATH="${pico-sdk-with-sm}/lib/pico-sdk/"
            export CMAKE_PREFIX_PATH=$NIXPKGS_CMAKE_PREFIX_PATH
          '';
        };
      }
    );
}
