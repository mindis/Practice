# Django Practice 
# Django = a web application framework 
# Used in newspaper for Kansas (web application) 
# Projects:
#	Pinterest
#	The Onion
# 	mozilla.org
#	reddit 
# HTML interfaces to highly dynamic data stored in a database 
# Django is HTTP in, HTTP out 
# HTTP Request -> URLs -> VIEWS(models, templates) -> HTTP Response 

# To create first project using Django
# >> django-admin.py startproject Practice2
# It will create the setup files below
# in the folder Practice2
'''
settings.py => configuration for project, what database used, users who can use it, configuration details 
manage.py => command runner (won't ever edit this)
urls.py => starting point to configure urls 
__int__.py => For python to know can import into module 

'''
# Go into the Practice 2 directory and run this: 
# >> python manage.py runserver
# Go to the web browser and server 
# >> http://localhost:8000/

Now run 
>> python manage.py startapp story 
This creates a new app called story 
>> find story 
You get a bunch of new files 
views.py
__init__.py # ignore this, makes it a module 
tests.py # This is where you put all your test cases 
models.py 

# Now add story to settings.py 
INSTALLED_APPS = (
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'story',
)

www.sooncheeloong.com/foo/ 
=> All web frameworks => Lets you map foo/ to some code to do something  
Django uses URLs to do this 

Uses regular expression to map a path that is coming in and uses a view to work with that regular expression 

Now go into urls.py, and uncomment/insert the lines below 

urlpatterns = patterns('',
    # Examples:
    url(r'^$', 'Practice2.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', include(admin.site.urls)),
)

Add this to story/views.py 

from django.http import HttpResponse

def home(request): 
	return HttpResponse("Hello World!") 

