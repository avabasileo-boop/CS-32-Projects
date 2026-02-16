void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if (m->menuItems() == nullptr)
    {

        cout << path << endl;
    }
    else
    {
  
        if (path != "")
        {
            cout << path << endl;
        }
       


        const vector<MenuItem*>& items = *(m->menuItems());
        for (size_t i = 0; i < items.size(); i++)
        {

            if ((path != "") && (m->menuItems()->size() > 0))
            {
                listAll(items[i], path + '/' + items[i]->name()); //recursive call to listAll
            }
            else
            {
                listAll(items[i], path + items[i]->name()); //recursive call to listAll
            }
        }
    }
}


