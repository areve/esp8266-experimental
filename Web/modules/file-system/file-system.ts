import * as $ from 'jquery'

$(() => {
  let testButton = $('<button>Test Button</button>')
    .click(() => {
      $.post('/ts?rename=fam.jpg&name=fam2.jpg')
        .done(() => {
          console.log('foo done')
          location.reload()
        })
        .fail(function () {
          console.log('error')
        })
    })
    
  $('section.file-system').append(testButton)

  $('section.file-system ul li')['sort'](function(a, b) {
    return ($(b).text().toLowerCase()) < ($(a).text().toLowerCase()) ? 1 : -1;
  }).appendTo('section.file-system ul')
})
