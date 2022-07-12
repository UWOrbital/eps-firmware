# GPIO App

Toggles custom GPIO pin defined in the board overlay found in `../overlays` on and off with constant period. 

For the blackpill_f411ce this app will toggle pin PC14. 

Build with the overlay file:

```
bash new_build.sh -p gpio -b blackpill_f411ce -o overlays/blackpill_f411ce.overlay

```

