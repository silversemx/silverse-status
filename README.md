# Silverse Status Service

### Development
```
sudo docker run \
  -it \
  --name silverse --rm \
  -p 5001:5001 \
  -v /home/ermiry/Documents/ermiry/Projects/silverse-status:/home/silverse \
  -e RUNTIME=development \
  -e PORT=5001 \
  -e CERVER_RECEIVE_BUFFER_SIZE=4096 -e CERVER_TH_THREADS=4 \
  -e CERVER_CONNECTION_QUEUE=4 \
  ermiry/silverse-status:development /bin/bash
```

## Routes

### Main

#### GET /silverse
**Description:** Silverse service top level route \
**Returns:**
  - 200 on success

#### GET /silverse/version
**Access:** Public \
**Description:** Returns silverse service current version \
**Returns:**
  - 200 and version's json on success
