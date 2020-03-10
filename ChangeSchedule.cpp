#include "stdafx.h"
#include "ChangeSchedule.h"
#include "ScheduleWindow.h"

void ChangeSchedule::OnMouseDown()
{
	if (object->GetName() == "Up")
	{
		Notify(MTYPE::SCHEDULE_UP, object->GetTag());
	}
	else if( object->GetName() == "Down")
	{
		Notify(MTYPE::SCHEDULE_DOWN, object->GetTag());
	}
}