
#include "GimmickWindow.h"

bool GimmickWindow::initGraphics()
{
	return false;
}

void GimmickWindow::onOpen()
{
	is_opened = true;
}

void GimmickWindow::onClose()
{
	is_opened = false;
}

void GimmickWindow::onComplete()
{
	is_opened = false;
	is_completed = true;
}

void GimmickWindow::mouseClick(Vector2 new_pos)
{
	is_mouse_held = true;
	mouse_pos = new_pos;
}

void GimmickWindow::mouseRelease()
{
	is_mouse_held = false;
}