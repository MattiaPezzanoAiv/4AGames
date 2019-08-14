/*


goal: bullet manager can accept fire in multithread and has in main thread an update method to simulate the world

bullet manager:
the concept is to have two different buffersm one to read and one to write
the fire method can access only the write buffer, then the update method can access only the read buffer.
in this way I can render using the read buffer after update(), and safely access the write buffer for the next update with the fire method

update(): this method is responsible to simulate a step of the "physics" world.

fire(): this method lock the access to the write buffer and instantiate a new bullet.










*/