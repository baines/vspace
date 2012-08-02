#include "renderer.h"
#include <assert.h>
#include <iostream>

SDL_Surface* Renderer::s_screen = NULL;
std::map<std::string,Image>* Renderer::m_sprites = new std::map<std::string,Image>;

#define current sprites->front()

void Renderer::init(int w, int h, std::string caption)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		fprintf(stderr, "Unable to initalise SDL: %s\n", SDL_GetError());
		exit(1);
	}
		
	atexit(SDL_Quit);
		
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
	putenv((char*)"SDL_VIDEO_CENTERED=center");
	SDL_WM_SetCaption(caption.c_str(), NULL);
	
	if (!(s_screen = SDL_SetVideoMode(w,h, 32, SDL_OPENGL | SDL_ANYFORMAT))){
		fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
		exit(1);
	}
	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	loadImage("ship.png");
	loadImage("asteroid.png");
	loadImage("bullet.png");
}

void Renderer::draw(std::queue<Sprite*>* sprites)
{
	int w,h;
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	while(!sprites->empty())
	{
		w = current->width/2;
		h = current->height/2;
		
		glPushMatrix();
		glTranslatef(current->x, current->y, 0);
		glRotatef(current->rotation,0.0f,0.0f,1.0f);
		glColor4f(current->colour.r,current->colour.g,current->colour.b,current->alpha);
		glBindTexture(GL_TEXTURE_2D, current->img.texture);		
		glBegin(GL_QUADS);
			glTexCoord2f(current->texX,current->texY); glVertex2f(-w,-h);
			glTexCoord2f(current->texW,current->texY); glVertex2f(w,-h);
			glTexCoord2f(current->texW,current->texH); glVertex2f(w,h);
			glTexCoord2f(current->texX,current->texH); glVertex2f(-w,h);
		glEnd();
		glPopMatrix();
		sprites->pop();
	}
	
	SDL_GL_SwapBuffers();
}

void Renderer::toggleFullscreen()
{
	int flags = s_screen->flags;
	
	s_screen = SDL_SetVideoMode(0, 0, 0, s_screen->flags ^ SDL_FULLSCREEN);
	
	if(!s_screen && !(s_screen = SDL_SetVideoMode(0, 0, 0, flags)))
		exit(1);
}

Image Renderer::loadImage(std::string path)
{
	std::map<std::string, Image>::iterator spriteIt = m_sprites->find(path);

	if(spriteIt != m_sprites->end())
		return spriteIt->second;
		
	SDL_Surface* surface = IMG_Load(("./media/img/"+path).c_str());
	if (!surface){
		fprintf(stderr, "Missing image file: %s\n", path.c_str());
		exit(1);
	}
			
	int format, format2;
	GLint colors = surface->format->BytesPerPixel;
	if (colors == 4) {
		format = GL_RGBA;
		if (surface->format->Rmask == 0x000000ff) 
            format2 = GL_RGBA;
		else format2 = GL_BGRA_EXT;
	} else
        if (colors == 3) {
		    format = GL_RGB;
		    if (surface->format->Rmask == 0x000000ff) 
          format2 = GL_RGB;
		    else 
          format2 = GL_BGR_EXT;
	} else {
		printf("Image is not truecolour: %s\n", path.c_str());
	}

	GLuint texture;		
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexImage2D( GL_TEXTURE_2D, 0, format,
		     surface->w, surface->h, 0, format2,
		      GL_UNSIGNED_BYTE, surface->pixels );
	
	Image img;
	img.texture = texture;
	img.width = surface->w;
	img.height = surface->h;
	
	SDL_FreeSurface(surface);	
	m_sprites->insert(std::pair<std::string,Image>(path,img));
	
	return img;
}

void Renderer::deleteTexture(std::string path)
{
	std::map<std::string, Image>::iterator spriteIt = m_sprites->find(path);
	
	if(spriteIt != m_sprites->end()){
		glDeleteTextures(1, &(spriteIt->second).texture);
		m_sprites->erase(spriteIt);
	}
}

void Renderer::quit()
{
	for(std::map<std::string, Image>::const_iterator itr = m_sprites->begin(); itr != m_sprites->end(); ++itr){
		glDeleteTextures(1,&(itr->second).texture);
	}
	
	delete m_sprites;
}
