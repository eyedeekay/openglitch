
build: convert
	./build.sh
	mv a.out bin/openglitch

clean:
	rm -rf bin/* obj/* */*.gch

docker-build:
	docker build -f Dockerfile -t eyedeekay/openglitch .

make:
	@echo "clang++ \\"
	@grep "directory" openglitch.cbp | sed 's|Add directory="|-I|g' | sed 's|" />| \\|g' | tr -d '\t' | sed 's|<| |g'
	@grep "option" openglitch.cbp | sed 's|Add option="||g' | sed 's|" />| \\|g' | tr -d '\t' | sed 's|<| |g' | sort -u
	@grep "library" openglitch.cbp | sed 's|Add library="|-l|g' | sed 's|" />| \\|g' | tr -d '\t' | sed 's|<| |g' | sort -u
	@echo "main.cpp src/*.cpp include/*.h"

convert:
	make -s make | tee build.sh
	chmod +x build.sh

docker-run: docker-build
	docker run --rm -i -t -d \
		-e DISPLAY=$(DISPLAY) \
		-e VERSION="$(BROWSER_VERSION)" \
		--name openglitch \
		--volume /tmp/.X11-unix:/tmp/.X11-unix:ro \
		--volume $(browser):/home/anon/tor-browser_en-US/Browser/Desktop \
		eyedeekay/openglitch
