scheeloong is a project, it can contain >= 1 apps. 
scheeloong/scheeloong is an app, it is one of the many apps that can be added to this project. 
anything in same directory as manage.py is an app, the parent directory of manage.py is the project (the website) 
app is a feature in the project. 


# Each time you update the database
>> python manage.py syncdb 
>> python manage.py runserver localhost:3000
Open browser to: localhost:3000/admin
And you can control admin settings 


# Need to disable cache on google chrome so static files get updated
http://stackoverflow.com/questions/5690269/disabling-chrome-cache-for-website-development


# Or if that doesn't work, clear browsing data for cache only 


# If that doesnt work, refresh your google chrome browser for static files by typing: 
CTRL + F5 

