#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

bool TextureManager::loadTexture(std::string id, std::string filePath)
{
	bool success = true;

	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());

	if (loadedSurface == nullptr)
	{
		printf("Error loading the texture (%s)! SDL_Error: %s\n", filePath.c_str(), SDL_GetError());
		success = false;
	}
	else
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), loadedSurface);

		if (texture == nullptr)
		{
			printf("Error creating the texture! SDL_Error: %s", SDL_GetError());
			success = false;
		}
		else
		{
			textureMap[id] = texture;
		}
	}

	return success;
}

void TextureManager::dropTexture(std::string id)
{
	SDL_DestroyTexture(textureMap[id]);
	textureMap.erase(id);
}

void TextureManager::draw(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = {0, 0, w, h};
	SDL_Rect dstRect = {x, y, w, h};

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect dstRect = { x, y, width, height };

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

TextureManager* TextureManager::getInstance()
{
	return instance = (instance != nullptr) ? instance : new TextureManager();
}

void TextureManager::clean()
{
	std::map<std::string, SDL_Texture*>::iterator iter;

	for (auto& texture : textureMap)
	{
		SDL_DestroyTexture(texture.second);
	}

	textureMap.clear();
}
