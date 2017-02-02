@echo off

rem # This script allows you to run OSHA related tests on your existing instance (created with install.sh, btw)
rem #
rem # Usage patterns
rem #    * run specific test method: ./test.sh ClassNameTest testFunctionName1,testFunctionName2
rem #    * run all tests from a class: ./test.sh ClassNameTest
rem #    * run all tests from specific group: ./test.sh OSHA
rem #    * run all tests from OSHA group: ./test.sh

FOR /F "tokens=* USEBACKQ" %%F IN (`drush php-script scripts/get_config_param.php xxx uri`) DO (
    SET uri=%%F
)

cd docroot

call drush en -y simpletest
call drush dis -y apachesolr

IF "%1"=="" GOTO ALL
IF "%2"=="" GOTO CLASS
GOTO METHOD

:ALL
    echo "Stand back! I'm running ALL the tests from group OSHA ..."
    call drush test-run --uri=%uri% OSHA
    goto DONE
:CLASS
    echo "Running tests from group/class %1 ..."
    call drush test-run --uri=%uri% %1
:METHOD
    echo "Running test %1 %2..."
    call drush test-run --uri=%uri% %1 --methods=%2
:DONE
cd ..