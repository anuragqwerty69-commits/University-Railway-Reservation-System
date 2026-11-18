# Railway Reservation System - Test Cases

| ID | Test scenario | Expected result |
|---|---|---|
| TC01 | Start application with empty data folder | Sample train catalogue is created |
| TC02 | View all trains | Train number, route, time, capacity and fare are shown |
| TC03 | Search valid source/destination | Matching direct trains are listed |
| TC04 | Search unavailable route | No direct train message appears |
| TC05 | Book ticket when seats are available | Unique PNR and confirmed seat are assigned |
| TC06 | Book beyond configured capacity | Booking is waitlisted |
| TC07 | Check an existing PNR | Current booking status is displayed |
| TC08 | Check an unknown PNR | Clear error message is displayed |
| TC09 | Cancel a confirmed booking | Booking becomes cancelled |
| TC10 | Cancel when a waitlist exists | Earliest waitlisted booking is promoted |
| TC11 | Cancel same PNR twice | Error is displayed; no second cancellation |
| TC12 | Restart application | Train and booking records persist |
| TC13 | Enter invalid passenger age | Passenger validation rejects the input |
| TC14 | Enter unknown train number | Booking is rejected with an error |

For final evaluation, execute these cases and attach screenshots of actual program output.
