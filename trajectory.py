
import gmplot
import webbrowser

def Convert(string):
    li = list(string.split(","))
    return li

latitude = input("Enter latitude list:")
latitude = Convert(latitude)

longitude = input("Enter longitude list:")
longitude = Convert(longitude)

map = input("Enter map type [roadmap(1) ,satellite(2) ,hybrid(3)]:")

if(int(map) == 1):
    map = "roadmap"
elif(int(map) == 2):
    map = "satellite"
elif(int(map) == 3):
    map = "hybrid"
else:
    print("You have not enter correct number the default map type is roadmap")
    map = "roadmap"

#latitude = [ 30.063593, 30.063564,30.064136,30.06466034270491,30.06490628717622,30.064819260740865,30.06468304529708 ]
#longitude = [31.281269, 31.281095, 31.280825, 31.28062297711093, 31.280496190044612, 31.28027759165441, 31.280115828845663 ]

if(len(latitude) != len(longitude)):
    print("Latitude list length must be equal to longitude list length")
else:
    for i in range(0, len(latitude)):
        latitude[i] = float(latitude[i])
        longitude[i] = float(longitude[i])

    gmap3 = gmplot.GoogleMapPlotter(latitude[0], longitude[0], 20,map_type=map)
    
    gmap3.scatter( latitude, longitude, '#FF0000',
                                size = 0.5, marker = False )
    
    gmap3.plot(latitude, longitude, 
            'cornflowerblue', edge_width = 2.5)
    
    gmap3.draw("map.html" )

    print("DONE!")

    webbrowser.open("map.html")
    input()
