#! /usr/bin/ruby
# coding: utf-8

buf = [] 
doxy = 0
example = 0

def commentblock(buf)
    unless buf == []	
      print "/** "	
      buf.each do |i| print i end
      print "*/\n"	
    end	
   end	

while gets

  $_.gsub!("@seealso", "@par 参照:")
  $_.gsub!("@errors", "@par エラー:")
  $_.gsub!("@returns", "@par 戻り値:")
  $_.gsub!("@return", "@par 戻り値:")
 #let doxygen find functions
  $_.gsub!(/[a-zA-Z_]\s\(\)/) {|m| m.delete!(" ")}
 #make variables in function descriptions shown in bold
  $_.gsub!(/\$[A-Z_]+/) {|m| m.delete!("$").reverse.downcase!.concat(" b@").reverse}

  if example == 1
     case $_ 
      when /#endif/
        buf.push($_.gsub!(/#endif/, "@endcode"))
	example = 0
      else	
        buf.push($_)
    end

    else  # when example == 0

     case  $_

      when /^\s*$/
	 if doxy == 1                       # empty line in doxygen comment
            buf.push($_)
	    end

      when /\/\*=\*\//                      #/*=*/ (flush)
	commentblock(buf)
    	buf = []

      when /^\/\*\s.*\*\//	# /* comment */ type comment 
#	if doxy == 1		
#	  # should be included only in the example code
#	  ## We used to do the following substituion as a workaround of
#	  ## a Doxygen bug.
# 	  ## buf.push($_.gsub!(/\*\//, " ").gsub!(/\/\*/, "//"))
#	  buf.push($_)
#	end

      when /\/\*\s.*\*\//	# code + /* comment */ type comment
#	if doxy == 1		
#	  # should be included in the example code
#	  ## See the above comment.
#	  ## buf.push($_.gsub!(/\*\//, " ").gsub!(/\/\*/, "//"))
#	  buf.push($_) # should be included in the example code
#	else
          if doxy == 0 
	    commentblock(buf)
 	    buf = []
 	    print $_.gsub!(/\/\*\s.*\*\//," ") # should be omiited in code
#	  end
	end

     when /\/\*{2,3}en.*\*\//	#english one liner is omitted
     when /\/\*\*ja.*\*\//	#one liner
     when /\/\*\*\*ja.*\*\//	#one liner
        buf.push($_.gsub!(/\/\*+ja/, " ").gsub!(/ *\*\//, "")).push("\n")
     when /\/\*\*\s.*\*\//	#one liner
     when /\/\*\*\*\s.*\*\//	#one liner
        buf.push($_.gsub!(/\/\*+/, " ").gsub!(/ *\*\//, "")).push("\n")

     when /\/\*{1,2}\s|\/\*{2,3}en|\/\*\*ja/  #this is not for Ja nor users
	doxy = -1
     when /\/\*\*\*ja/
        buf.push($_.gsub!(/\/\*+ja/, " "))
	doxy = 1
     when /\/\*\*\*/	
        buf.push($_.gsub!(/\/\*+/, " "))
	doxy = 1

     when /EXAMPLE_CODE/ 
	#start example code lines
        buf.push($_.gsub!(/#if EXAMPLE_CODE/, "\n \n @par 例： \n @code"))
	example = 1

     when /\*\//
	if doxy == 1
           buf.push($_.gsub!(/ *\*\//, ""))
	end
        doxy = 0
     else 
	case doxy 
	  when -1
  	  when 1	
           buf.push($_) 
	  else 
       	   commentblock(buf)
    	   buf = []
	   print($_)
        end
     end
   end
end

commentblock(buf)

# Local Variables:
# coding: utf-8
# End:
