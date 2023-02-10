const autoFeedOption = document.querySelector("input#choice")
const formSection = document.querySelector('div.form-section')
const timeInputs = document.querySelectorAll('input[type=time]')

let displayed = formSection.style.display !== 'none'
autoFeedOption.onclick = () => {
    if (displayed) {
        formSection.style.display = 'none'
        displayed = false
    } else {
        formSection.style.display = ''
        displayed = true
    }
    timeInputs.forEach((timeInput) => {
        timeInput.toggleAttribute("required")
    })
}
