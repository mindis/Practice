# To debug curl-server interaction a little, use -v (verbose)
curl -v www.google.com
# To debug curl-server interaction in detail
curl --trace-ascii temp.txt http://www.example.com/

# If need to pass username and password using HTTP authentication for service, 
curl -u yourusername:yourpassword http://example.org/

# To send different request on single line, use --next
# e.g. HEAD then GET 
# curl -I www.google.com --next www.google.com 

#--------------------------------------------------------------------------------
# GET
#--------------------------------------------------------------------------------
# GET the HTML for a webpage
curl http://curl.haxx.se
# To get response header as well that are hidden, use -i (--include)
curl -i http://curl.haxx.se
# To get response header only, use -I (note: Some webservers prevent this)
curl -I http://curl.haxx.se
# To send GETS to multiple urls, just space delimit them
curl -I www.google.com www.yahoo.com

#--------------------------------------------------------------------------------
# POST (create)
#--------------------------------------------------------------------------------
# To send data, use -d (--data)
curl -d name=curl www.example.com 

# To url-encode POST data, use -urlencode
curl --data-urlencode "name=I am a boy" www.example.com
    
# To send json data, inside a data.json file
# -d = --data, -H = --header
curl -H "Content-Type: application/json" -X POST -d @data.json www.example.com

#--------------------------------------------------------------------------------
# PUT (update)
# --------------------------------------------------------------------------------
curl -v -X PUT -d "data here" www.example.com

#--------------------------------------------------------------------------------
# DELETE 
#--------------------------------------------------------------------------------
curl -v -X DELETE /clients/alex www.example.com push -u origin maste
