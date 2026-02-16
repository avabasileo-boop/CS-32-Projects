
void removeBad(list<Restaurant*>& li)
{

	list<Restaurant*>::iterator p = li.begin();

	while (p != li.end())
	{
		if ((*p)->stars() <= 2)
		{
			list<Restaurant*>::iterator tempIterator = p;
			delete* tempIterator;
			p = li.erase(p);
		}
		else
		{
			p++;
		}
	}
}
