# Πίνακας ελέγχου έξυπνης πόλης

Η έξυπνη πόλη μας,στέλνει συνέχεια δεδομένα στον πίνακα έλεγχου που υλοποιείται χρησιμοποιώντας την ανοικτή δωρεάν πλατφόρμα adafruit.io .
Σ αυτην την πλατφόρμα δημιουργήσαμε οθόνες παρακολούθησης και ειδοποίησης(alert) και έτσι συγκεντρώνουμε τα δεδομένα που μας στέλνουν οι διάφοροι
αισθητήρες της πόλης κ γνωρίζουμε τι συμβαίνει σε κάθε σημείο που παρακολουθούμε.
Αφου φτιάξεις λογαριασμό στην πλατφόρμα, ορίζεις τις ροές δεδομένων που θα έχεις (feeds) και τις συνδέεις με συγκεκριμένες οθόνες στον πίνακα 
ελέγχου που δημιουργείς(dashboard). Καθώς έρχονται τα δεδομένα απ τους αισθητήρες απεικονίζονται στην αντίστοιχη οθόνη.Έτσι πχ τα δεδομένα του 
έξυπνου κάδου (σταθμη σκουπιδιών) έρχονται μέσα απ το feed https://io.adafruit.com/youraccount/feeds/garbage. Για να υπάρχει ασφάλεια στην επικοινωνία
τα esp8266 πρεπει να στέλνουν και το API key που ταυτοποιεί το χρήστη.Το API key μας το δίνει η πλατφόρμα κ έτσι μπορεί να ελέγχει ότι τα δεδομένα 
που έρχονται είναι απο μία συσκευή του εγγεγραμμένου χρήστη.
