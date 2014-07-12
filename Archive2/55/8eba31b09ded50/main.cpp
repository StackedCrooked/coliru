alias epoch_seconds='date +%s'
alias epoch_minutes='echo $(($(epoch_seconds) / 60))'
alias epoch_hours='echo $(($(epoch_minutes) / 60))'
alias epoch_days='echo $(($(epoch_hours) / 24))'
alias epoch_weeks='echo $(($(epoch_days) / 7))'



echo "days since epoch: $(epoch_days)"
echo "weeks since epoch: $(epoch_weeks)"
