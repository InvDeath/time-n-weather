<?php
/**
 * @file
 * Callbacks for administration page forms.
 */

/**
 * Creating form for module's form.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function timenweather_admin_settings($form, &$form_state, $no_js_use = FALSE) {
  $tempvar = variable_get('timenweather_admin_settings', NULL);
  if (empty($form_state['cities_count'])) {
    $form_state['cities_count'] = 1;
  }
  $form['#tree'] = TRUE;
  $form['cities'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('Cities to observe'),
    '#prefix' => '<div id="cities-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  for ($i = 1; $i <= $form_state['cities_count']; $i++) {
    $form['cities']['timenweather_settings_city_name_'.$i] = array(
      '#type'   => 'textfield',
      '#title'  => t('City ') . $i,
    );
    $form['cities']['timenweather_settings_city_time_'.$i] = array(
      '#type'   => 'checkbox',
      '#title'  => t('Show clock'),
    );
    $form['cities']['timenweather_settings_city_cache_'.$i] = array(
      '#type'   => 'checkbox',
      '#title'  => t('Cachable'),
    );
  }

  $form['cities']['add_city'] = array(
    '#type'   => 'submit',
    '#value'  => t('Add city'),
    '#submit' => array('timenweather_settings_city_addfield'),
    '#ajax'   => array(
      'callback'  => 'timenweather_admin_settings_callback',
      'wrapper'   => 'cities-fieldset-wrapper',
    ),
  );
  if ($form_state['cities_count'] > 1) {
    $form['cities']['remove_city'] = array(
      '#type'   => 'submit',
      '#value'  => t('Remove city'),
      '#submit' => array('timenweather_settings_city_remfield'),
      '#ajax'   => array(
        'callback'  => 'timenweather_admin_settings_callback',
        'wrapper'   => 'cities-fieldset-wrapper',
      ),
    );
  }
  return system_settings_form($form, TRUE);
}

function timenweather_admin_settings_callback($form, $form_state) {
  return $form['cities'];
}

function timenweather_settings_city_addfield($form, &$form_state) {
  $form_state['cities_count']++;
  $form_state['rebuild'] = TRUE;
}

function timenweather_settings_city_remfield($form, &$form_state) {
  $form_state['cities_count'] --;
  $form_state['rebuild'] = TRUE;
}  

/**
 * Submit form function.
 */
function timenweather_admin_settings_submit($form, &$form_state) {
  $tempvar2 = serialize($form_state);
  variable_set("timenweather_admin_settings", serialize($form_state));

  //$city = $form_state['values']['city_name'];
  //$isTime = $form_state['values']['city_time'];

  //variable_set('timenweather_settings_city', $city);
  //variable_set('timenweather_settings_time', $isTime);

  return true;
}