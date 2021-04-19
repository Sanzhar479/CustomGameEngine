#include "EventListener.h"
#include "../Core/CEngine.h"

EventListener::~EventListener() {

}
void EventListener::Update() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) {
			CEngine::GetInstance()->Exit();
		}
		switch (sdlEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			MouseEventListener::Update(sdlEvent);
			break;
		default:
			break;
		}
	}
}