import socket
import sys
from datetime import datetime

PORTS = [80, 443, 22, 25, 53]
TIMEOUT = 0.1 # 100ms


def scan(target):
    open_ports = []
    print("Scanning target: " + target)
    print("Time started: " + str(datetime.now()))

    for p in PORTS:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            s.settimeout(TIMEOUT)
            s.connect((target, p))
            print(f"Port {p}: Open")
            open_ports.append(p)
        except(socket.timeout, ConnectionRefusedError, OSError):
            print(f"Port {p}: Closed")
        finally:
            s.close()

    print(f"Open ports: {open_ports}")

if __name__ == "__main__":

    if len(sys.argv) == 2:
        try:
            target = socket.gethostbyname(sys.argv[1])
        except socket.gaierror:
            print("Error: Hostname could not be resolved")
            sys.exit(1)
    else:
        print("Invalid number of arguments. Add hostname or IP address")
        print("Usage: python3 port_scanner.py <ip-address>")
        sys.exit(1)
        
    scan(target)


# Port Scanner
''' Iterate through range of ports and 
attempting to connect to each of the ports 
ISP could have prohibited scans, otherwise can local
machine in LAN, WiFi router, VM
Submit PDF containing code and explanation,
demonstrate execution of code with example and
relevant screnshots

1. Able to pass IP address as cmd-line argument
2. Scans only ports 80, 443, 22, 25 and 53
3. Default timeout for port response to 0.1 sec (100ms)
4. Considered open when the connection is established,
   otherwise raise exception - try...catch
5. Print open ports for given IP address
'''
