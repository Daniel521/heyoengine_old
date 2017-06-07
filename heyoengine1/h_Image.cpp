#include "h_Image.h"
#include "h_Graphics.h"
#include <SDL_image.h>

namespace Heyo {

	bool Texture::loadTexture(std::string imgAddress, Graphics & graphics)
	{
		clear();

		// Load image at specified path
		SDL_Surface * loadedSurface = IMG_Load(imgAddress.c_str());
		if (loadedSurface == NULL) {
			SDL_Log("Unable to load image %s! SDL_image error: %s\n", imgAddress.c_str(), IMG_GetError());
			return false;
		}
		else {
			// Convert surface to screen format
			img_surface = SDL_ConvertSurface(loadedSurface, graphics.m_winSurface->format, NULL);
			SDL_SetColorKey(img_surface, SDL_TRUE, SDL_MapRGB(img_surface->format, 0, 0xFF, 0xFF));
			// Convert surface to texture
			img_texture = SDL_CreateTextureFromSurface(graphics.m_renderer, img_surface);

			// Misc information
			m_width = img_surface->w;
			m_height = img_surface->h;
			img_Rect.h = m_height;
			img_Rect.w = m_width;
			img_Rect.x = 0;
			img_Rect.y = 0;
			frameCount = 0;
			frame = 0;
			frameDivider = 0;

			// Get rid of old loaded surfaces
			SDL_FreeSurface(loadedSurface);

			return true;
		}
	}

	void Texture::clear()
	{
		if (img_surface != NULL) {
			SDL_FreeSurface(img_surface);
			img_surface = NULL;
		}
		if (img_texture != NULL) {
			SDL_DestroyTexture(img_texture);
			img_texture = NULL;
		}
		m_width = 0;
		m_height = 0;
		img_Rect.h = 0;
		img_Rect.w = 0;
		img_Rect.x = 0;
		img_Rect.y = 0;
		frameCount = 0;
		frame = 0;
		frameDivider = 0;
	}

	int Texture::getWidth()
	{
		return m_width;
	}

	int Texture::getHeight()
	{
		return m_height;
	}

	SDL_Rect Texture::getRect()
	{
		return img_Rect;
	}

	bool Texture::setRect(Rect clip)
	{
		if (clip.h > m_height || clip.w > m_width) {
			SDL_Log("Texture error: Passed Rect in setRect is out of bound.\n");
			return false;
		}

		img_Rect = clip;
		return true;
		
	}

	Texture::Texture()
	{
		// Initialize PNG loading
		clear();
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			SDL_Log("SDL_image could not initialize! SDL_image error: %s\n", IMG_GetError());
		}
	}

	Texture::~Texture()
	{
		clear();
	}

	

	Image::Image() : m_surface(NULL), m_texture(NULL), m_width(0), m_height(0), m_imgtype(0) // Done?
	{
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			SDL_Log("SDL_image could not initialize! SDL_image error: %s\n", IMG_GetError());
		}
	}

	Image::~Image()	// Done?
	{
		clear();
		IMG_Quit();
	}

	void Image::clear()	// Done?
	{
		if (m_surface != NULL) {
			SDL_FreeSurface(m_surface);
			m_surface = NULL;
		}
		if (m_texture != NULL) {
			SDL_DestroyTexture(m_texture);
			m_texture = NULL;
		}
		m_width = 0;
		m_height = 0;
	}

	bool Image::loadImage(std::string imgAddress, int imgType, Graphics & graphics)
	{
		if (m_surface != NULL)
			clear();

		// Load image at specified path
		SDL_Surface * loadedSurface = IMG_Load(imgAddress.c_str());
		if (loadedSurface == NULL) {
			SDL_Log("Unable to load image %s! SDL_image error: %s\n", imgAddress.c_str(), IMG_GetError());
			return false;
		}
		else {
			// Convert surface to screen format
			m_surface = SDL_ConvertSurface(loadedSurface, graphics.m_winSurface->format, NULL);
			// Get rid of old loaded surfaces
			SDL_FreeSurface(loadedSurface);
			SDL_SetColorKey(m_surface, SDL_TRUE, SDL_MapRGB(m_surface->format, 0, 0xFF, 0xFF));

			// Convert surface to texture
			m_texture = SDL_CreateTextureFromSurface(graphics.m_renderer, m_surface);

			// Misc information
			m_width = m_surface->w;
			m_height = m_surface->h;
			//img_Rect.h = m_height;
			//img_Rect.w = m_width;
			//img_Rect.x = 0;
			//img_Rect.y = 0;
			//frameCount = 0;
			//frame = 0;
			//frameDivider = 0;


			return true;
		}
	}

}