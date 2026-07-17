CONTAINERNAME := zmk-container

.PHONY: all left right shell settings-reset container clone

all: left right

left: container
	cd zmk && \
	podman run -it --rm \
		--security-opt label=disable \
		--workdir /workspaces/zmk/app \
		-v .:/workspaces/zmk \
		-v ../mica-shield-module:/workspaces/zmk-modules/mica-shield-module \
		-v ../mica-event-module:/workspaces/zmk-modules/mica-event-module \
		-p 3000:3000 \
		${CONTAINERNAME} /bin/bash -c ' \
		{ if [ ! -d "../.west" ]; then west init -l . && west update; fi } && \
		west build -p -d ../build/left -b nice_nano_v2 -- \
			-DZMK_EXTRA_MODULES="/workspaces/zmk-modules/mica-shield-module;/workspaces/zmk-modules/mica-event-module" \
			-DZMK_CONFIG="/workspaces/zmk-modules/mica-shield-module/config" \
			-DSHIELD=mica_left \
		' \
	&& mkdir -p ../build \
	&& cp build/left/zephyr/zmk.uf2 ../build/zmk_left.uf2

right: container
	cd zmk && \
	podman run -it --rm \
		--security-opt label=disable \
		--workdir /workspaces/zmk/app \
		-v .:/workspaces/zmk \
		-v ../mica-shield-module:/workspaces/zmk-modules/mica-shield-module \
		-v ../mica-event-module:/workspaces/zmk-modules/mica-event-module \
		-p 3000:3000 \
		${CONTAINERNAME} /bin/bash -c ' \
		{ if [ ! -d "../.west" ]; then west init -l . && west update; fi } && \
		west build -p -d ../build/right -b nice_nano_v2 -- \
			-DZMK_EXTRA_MODULES="/workspaces/zmk-modules/mica-shield-module;/workspaces/zmk-modules/mica-event-module" \
			-DZMK_CONFIG="/workspaces/zmk-modules/mica-shield-module/config" \
			-DSHIELD=mica_right \
		' \
	&& mkdir -p ../build \
	&& cp build/right/zephyr/zmk.uf2 ../build/zmk_right.uf2

settings_reset: container
	cd zmk && \
	podman run -it --rm \
		--security-opt label=disable \
		--workdir /workspaces/zmk/app \
		-v .:/workspaces/zmk \
		-v ../mica-shield-module:/workspaces/zmk-modules/mica-shield-module \
		-v ../mica-event-module:/workspaces/zmk-modules/mica-event-module \
		-p 3000:3000 \
		${CONTAINERNAME} /bin/bash -c ' \
		{ if [ ! -d "../.west" ]; then west init -l . && west update; fi } && \
		west build -p -d ../build/settings_reset -b nice_nano_v2 -- \
			-DZMK_EXTRA_MODULES="/workspaces/zmk-modules/mica-shield-module;/workspaces/zmk-modules/mica-event-module" \
			-DZMK_CONFIG="/workspaces/zmk-modules/mica-shield-module/config" \
			-DSHIELD=settings_reset \
		' \
	&& mkdir -p ../build \
	&& cp build/settings_reset/zephyr/zmk.uf2 ../build/zmk_settings_reset.uf2

shell: container
	cd zmk && \
	podman run -it --rm \
		--security-opt label=disable \
		--workdir /workspaces/zmk \
		-v ../mica-shield-module:/workspaces/zmk-modules/mica-shield-module \
		-v ../mica-event-module:/workspaces/zmk-modules/mica-event-module \
		-p 3000:3000 \
		${CONTAINERNAME} /bin/bash
	
container: clone
	cd zmk && \
	podman build -t $(CONTAINERNAME) -f Dockerfile .devcontainer

clone:
	git submodule update --init --recursive
