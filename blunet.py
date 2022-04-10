#!/usr/bin/env python
# coding: utf-8

# ## Bluetooth connection module

# In[160]:


"""
import necessary liberaries
"""
import bluetooth, subprocess


# In[158]:


"""
Get the address of a given name if found
"""
def get_address(check_name):
    nearby_devices = bluetooth.discover_devices(lookup_names=True, flush_cache = True)
    for addr, name in nearby_devices:
        #print("  {} - {}".format(addr, name))
        if(name == check_name):
            print("Bluetooth module found")
            return addr
    return False


# In[159]:


"""
Function that takes the name of the bluetooth module to connect to and its password
and returns a connection object
"""
def connect(name, passkey):
    addr = get_address(name)
    port = 1         # RFCOMM port
    
    # kill any "bluetooth-agent" process that is already running
    subprocess.call("kill -9 `pidof bluetooth-agent`",shell=True)

    # Start a new "bluetooth-agent" process where XXXX is the passkey
    status = subprocess.call("bluetooth-agent " + passkey + " &",shell=True)

    # Now, connect in the same way as always with PyBlueZ
    try:
        s = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        s.connect((addr,port))
        print("Connected Successfully")
        return s
    except bluetooth.btcommon.BluetoothError as err:
        # Error handler
        print("Cant connect to bluetooth module")


# In[155]:


"""
Function that takes a connection object and data to send to the bluetooth module and an optional buffer size
"""
def send(conn, data, buffer = 1024):
    conn.recv(buffer)
    conn.send(data)


# In[ ]:




