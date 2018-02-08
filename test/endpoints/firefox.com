# Hostname of the endpoint : this can be a url or an ip adress
Hostname=firefox.com

# Username to use on default conexion
Username=hector

# Default port to use for conexion
Port=22

# List of comma separated usernames. Thoose user are allowed to go to the endpoint
Allowed_users=hector,martin
