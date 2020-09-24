#include "TextureManager.h"
#include "Camera.h"

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

bool TextureManager::parseTextures(std::string source)
{
	tinyxml2::XMLDocument doc;

	doc.LoadFile(source.c_str());

	if (doc.Error())
	{
		printf("Error loading the texture (%s)!\n", source.c_str());
		return false;
	}

	tinyxml2::XMLElement* root = doc.RootElement();
	
	for (tinyxml2::XMLElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
	{
		if (element->Value() == std::string("texture"))
		{
			std::string id = element->Attribute("id");
			std::string src = element->Attribute("source");
			loadTexture(id, src);
		}
	}

	return true;
}

void TextureManager::dropTexture(std::string id)
{
	SDL_DestroyTexture(textureMap[id]);
	textureMap.erase(id);
}

void TextureManager::draw(std::string id, int x, int y, int w, int h, float scaleX = 1, float scaleY = 1, float scrollSpeed, SDL_RendererFlip flip)
{
	Vector2D camera = Camera::getInstance()->getCurrentPosition() * scrollSpeed;

	SDL_Rect srcRect = { 0, 0, w, h };
	SDL_Rect dstRect = { x - camera.getX(), y - camera.getY(), w * scaleX, h * scaleY};

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	Vector2D camera = Camera::getInstance()->getCurrentPosition();

	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect dstRect = { x - camera.getX(), y - camera.getY(), width * 1.5, height * 1.5};

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::drawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	Vector2D camera = Camera::getInstance()->getCurrentPosition();

	SDL_Rect srcRect = { tileSize * frame, tileSize * row, tileSize, tileSize };
	SDL_Rect dstRect = { x - camera.getX(), y - camera.getY(), tileSize, tileSize };

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), textureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
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
