program convert_to_csv
implicit none

    ! Flags to handle edge cases. file_exists handles checking if the demo file exists and can be read, read_eof handles reaching the end of the demo file
    ! and skip_first_instance prevents the program from trying to write a dummy datapoint to the csv on reaching the first time label
    logical :: file_exists, read_eof, skip_first_instance
    ! print_<label> variables store the string to print out for the current raw datapoint, and print_row stores the final combined string to write to file
    ! io_buffer stores inputs read from the demo file
    character(len = 64) :: io_buffer, print_time, print_amplitude, print_direction, print_row
    ! value_target is an encoding to record what the most recent label read was to record values it reads correctly
    ! Encoding is 1 = time, 2 = direction, 3 = amplitude
    integer :: eof_error, value_target

    inquire(file="data/output.demo", exist=file_exists)

    read_eof = .TRUE.
    skip_first_instance = .TRUE.

    if (.not. file_exists) then
        print *, "Missing raw output file"
        call EXIT(1)
    end if

    ! By default fortran does not overwrite files, so must manually delete old file to create fresh csv
    inquire(file="data/output.csv", exist=file_exists)
    if (file_exists) then
        open(3, file="data/output.csv", status="old")
        close(3, status="delete")
    end if

    open(1, file="data/output.demo", status="old")
    open(2, file="data/output.csv", status="new")
    write(2, *) "time,direction,amplitude"
    
    do while (read_eof)
        read(1, '(a)', iostat = eof_error) io_buffer
        if (eof_error == 0) then
            if (io_buffer == "time") then
                value_target = 1
                if (.not. skip_first_instance) then
                    print_row = trim(print_time)//","//trim(print_direction)//","//trim(print_amplitude)
                    write(2, *) trim(print_row)
                end if
                print_time = "undefined"
                print_direction = "undefined"
                print_amplitude = "undefined"
                skip_first_instance = .FALSE.
            else if (io_buffer == "direction") then
                value_target = 2
            else if (io_buffer == "amplitude") then
                value_target = 3
            else if (.not. io_buffer == "") then
                if (value_target == 1) then
                    read(io_buffer, *) print_time
                else if (value_target == 2) then
                    read(io_buffer, *) print_direction
                else if (value_target == 3) then
                    read(io_buffer, *) print_amplitude
                else
                    print *, "Value found before target specifier"
                    call EXIT(1)
            end if
        end if
        else if (eof_error == -1) then ! -1 thrown if end of file, -2 thrown for other read errors
            read_eof = .FALSE.
            if (.not. skip_first_instance) then
                print_row = trim(print_time)//","//trim(print_direction)//","//trim(print_amplitude)
                write(2, *) trim(print_row)
            end if
        else if (eof_error == -2) then
            print *, "Read failed"
            call EXIT(1)
        end if
    end do

    close(1)
    close(2)

end program convert_to_csv