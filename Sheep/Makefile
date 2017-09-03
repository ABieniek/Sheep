COMPILER = clang++
LINKER = clang++

CFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all: sheep

sheep: main.o
	$(COMPILER) $(CFLAGS) main.o Game.o ResourceManager.o InputHandler.o -o sheep

Game.o: Game.h Game.cpp
	$(COMPILER) $(CFLAGS) TextUtil.o ResourceManager.o SpriteRenderer.o Drawable.o
	Unit.o Flock.o CollisionUtil.o Hazard.o Rocket.o Lazer.o HazardHandler.o
	PowerUp.o Button.o InputHandler.o

ResourceManager.o: ResourceManager.h ResourceManager.cpp
	$(COMPILER) $(CFLAGS) Texture2D.o Shader.o

InputHandler.o: InputHandler.h InputHandler.cpp
	$(COMPILER) $(CFLAGS) InputHandler.h InputHander.cpp

TextUtil.o: TextUtil.h TextUtil.cpp
	$(COMPILER) $(CFLAGS) Shader.o

ResourceManager.o: ResourceManager.h ResourceManager.cpp
	$(COMPILER) $(CFLAGS) Shader.o Texture2D.o

SpriteRenderer.o: SpriteRenderer.h SpriteRenderer.cpp
	$(COMPILER) $(CFLAGS) Texture2D.o Shader.o

Drawable.o: Drawable.h Drawable.cpp
	$(COMPILER) $(CFLAGS) Texture2D.o SpriteRenderer.o

Unit.o: Unit.h Unit.cpp
	$(COMPILER) $(CFLAGS) Drawable.o

Flock.o: Flock.h Flock.cpp
	$(COMPILER) $(CFLAGS) Unit.o CollisionUtil.o

CollisionUtil.o: CollisionUtil.h CollisionUtil.cpp
	$(COMPILER) $(CFLAGS) Unit.o

Hazard.o: Hazard.h Hazard.cpp
	$(COMPILER) $(CFLAGS) Texture2D.o SpriteRenderer.o Drawable.o Unit.o

Rocket.o: Rocket.h Rocket.cpp
	$(COMPILER) $(CFLAGS) Hazard.o Unit.o CollisionUtil.o

Lazer.o: Lazer.h Lazer.cpp
	$(COMPILER) $(CFLAGS) Hazard.o Unit.o CollisionUtil.o

HazardHandler.o: HazardHandler.h HazardHandler.cpp
	$(COMPILER) $(CFLAGS) Texture2D.o Hazard.o Rocket.o Lazer.o

PowerUp.o: PowerUp.h PowerUp.cpp
	$(COMPILER) $(CFLAGS) Drawable.o Unit.o CollisionUtil.o

Button.o: Button.h Button.cpp
	$(COMPILER) $(CFLAGS) Drawable.o

Shader.o: Shader.h Shader.cpp
	$(COMPILER) $(CFLAGS)

Texture2D.o: Texture2D.h Texture2D.cpp
	$(COMPILER) $(CFLAGS)
