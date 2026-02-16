
void removeEven(list<int>& li)
{
	for (list<int>::iterator p = li.begin(); p != li.end(); )
	{

		if (!(*p % 2))
		{
			//you must use list's erase member funciton  
			p = li.erase(p); 
		}
		else
		{
			p++;
		}

		
	}
}
