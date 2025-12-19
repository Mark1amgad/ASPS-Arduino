Note on Controller Responsibilities

This project uses two Arduino Uno boards. While each controller has a primary responsibility
(Gate & Access control vs. Parking & Safety monitoring), some logic such as slot state handling,
LCD updates, and access-related routines may appear in both sketches. This overlap is intentional
and was chosen to simplify deployment, standalone testing, and hardware validation. It does not
indicate a design error or incomplete separation, and the code reflects a finalized, working
hardware implementation.
