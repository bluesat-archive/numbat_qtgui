# Message that reports the position, and orientation of the robot
# Location specified using the WGS 84 reference ellipsoid

#Based on the NavSatFix message here: http://docs.ros.org/api/sensor_msgs/html/msg/NavSatFix.html


# Latitude [degrees]. Positive is north of equator; negative is south.
float64 latitude

# Longitude [degrees]. Positive is east of prime meridian; negative is west.
float64 longitude


# Altitude [m]. Positive is above the WGS 84 ellipsoid
# (quiet NaN if no altitude is available).
float64 altitude

#The orientation of the front of the rover
#relative to grid North on the WGS 84 datum
#where 0 deg is Grid North
float64 orientation

#The pitch of the robot (facing forward), in degrees.
#0 being level to the horizon, and positive being facing above the horizon (nose up)
#rotation is around the centre of the robot
float64 pitch

#The roll of the robot (forward facing)
#0 deg is level with the horizon, Positive is left up
float64 roll

#The heading relative to the grid north. (WGS 84)
float64 heading


