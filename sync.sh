rsync -a \
    --exclude=client/node_modules \
    --exclude=server/__pycache__ \
    --exclude=*/.DS_Store \
    --exclude=.git \
    -i ~/.ssh/id_rsa \
    ~/Git/rgb_controller pi@192.168.178.150:~