# Simple Systemd service

- a service that will just print every 1 second

## Build & Run
1. Compile the app 
    ```bash
    gcc serviceapp.c -o serviceapp
    ```

2. copy the service unit file to `/etc/systemd/system`
    ```bash
    sudo cp myexample.service /etc/systemd/system
    ```

3. reload the daemon
    ```bash
    sudo systemctl daemon-reload
    ```

4. start the service
    ```bash
    sudo systemctl start myexample.service
    ``` 
5. Check the log
    ```bash
    cat /var/log/myexample.log
    ```