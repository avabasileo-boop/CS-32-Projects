
void removeBad(vector<Restaurant*>& v)
{

	vector<Restaurant*>::iterator it = v.begin();
	while (it != v.end())
	{
		if ((*it)->stars() <= 2)
		{
			vector<Restaurant*>::iterator temp = it;
			delete* temp;
			it = v.erase(it);
		}
		else
			it++;
	}

}
