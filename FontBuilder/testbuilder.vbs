set fs = createobject("scripting.filesystemobject")

lol = inputbox("Filename to create?")
if lol <> "" then
 set a = fs.createtextfile(lol)

 t = inputbox("Filename of the font pic")
 a.writeline t

 t = inputbox("Min char")
 a.write chr(t) + " "

 t = inputbox("Max char")
 a.writeline chr(t)

 t = inputbox("Bytes for width map")
 g = split(t, " ")
 
 for i = 0 to ubound(g) - 1
  a.write chr(g(i))
 next

 a.close

end if