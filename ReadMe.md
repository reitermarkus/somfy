# Somfy Telis 4 Remote API for ESP8266

## API

### `command`

- `up`:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;△
- `stop`:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⬜︎
- `down`:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;▽
- `switch`:&nbsp;○

### `channel`

- `0`: ⬛︎ ⬛︎ ⬛︎ ⬛︎
- `1`: ⬛︎ ⬜︎ ⬜︎ ⬜︎
- `2`: ⬜︎ ⬛︎ ⬜︎ ⬜︎
- `3`: ⬜︎ ⬜︎ ⬛︎ ⬜︎
- `4`: ⬜︎ ⬜︎ ⬜︎ ⬛︎

### Usage Examples

Press “up” key for channel 1.

```http
POST /
```

```json
{"channel": 1, "command": "up"}
```


Press “stop” key for channel 4.

```http
POST /
```

```json
{"channel": 4, "command": "stop"}
```

Press “down” key for channel 0.

```http
POST /
```

```json
{"channel": 0, "command": "down"}
```

Switch to channel 3.

```http
POST /
```

```json
{"channel": 3, "command": "switch"}
```
